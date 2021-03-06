/** Single source shortest paths -*- C++ -*-
 * @file
 * @section License
 *
 * Galois, a framework to exploit amorphous data-parallelism in irregular
 * programs.
 *
 * Copyright (C) 2011, The University of Texas at Austin. All rights reserved.
 * UNIVERSITY EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES CONCERNING THIS
 * SOFTWARE AND DOCUMENTATION, INCLUDING ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR ANY PARTICULAR PURPOSE, NON-INFRINGEMENT AND WARRANTIES OF
 * PERFORMANCE, AND ANY WARRANTY THAT MIGHT OTHERWISE ARISE FROM COURSE OF
 * DEALING OR USAGE OF TRADE.  NO WARRANTY IS EITHER EXPRESS OR IMPLIED WITH
 * RESPECT TO THE USE OF THE SOFTWARE OR DOCUMENTATION. Under no circumstances
 * shall University be liable for incidental, special, indirect, direct or
 * consequential damages or loss of profits, interruption of business, or
 * related expenses which may arise from use of Software or Documentation,
 * including but not limited to those resulting from defects in Software and/or
 * Documentation, or loss or inaccuracy of data of any kind.
 *
 * @section Description
 *
 * Single source shortest paths.
 *
 * @author Andrew Lenharth <andrewl@lenharth.org>
 */
#include "SSSPall.h"

#include "Galois/Timer.h"
#include "Galois/Statistic.h"
#include "Galois/Galois.h"
#include "Galois/UserContext.h"
#include "Galois/Graph/LCGraph.h"
#include "llvm/Support/CommandLine.h"

#include "Lonestar/BoilerPlate.h"

#include <iostream>
#include <set>

namespace cll = llvm::cl;

static const char* name = "Single Source Shortest Path";
static const char* desc =
  "Computes the shortest path from a source node to all nodes in a directed "
  "graph using a modified Bellman-Ford algorithm";
static const char* url = "single_source_shortest_path";

static cll::opt<std::string> filename(cll::Positional, cll::desc("<input file>"), cll::Required);
static cll::opt<int> stepShift("delta", cll::desc("Shift value for the deltastep"), cll::init(10));

typedef Galois::Graph::LC_InlineEdge_Graph<SNode, uint32_t>
  ::with_out_of_line_lockable<true>::type
  ::with_compressed_node_ptr<true>::type
  ::with_numa_alloc<true>::type
  Graph;
typedef Graph::GraphNode GNode;

typedef UpdateRequestCommon<GNode> UpdateRequest;

struct UpdateRequestIndexer
  : std::unary_function<UpdateRequest, unsigned int> {
  unsigned int operator() (const UpdateRequest& val) const {
    unsigned int t = val.w >> stepShift;
    return t;
  }
};

Graph graph;

struct process {
  typedef int tt_does_not_need_aborts;

  void operator()(UpdateRequest& req, Galois::UserContext<UpdateRequest>& lwl) {
    SNode& data = graph.getData(req.n,Galois::MethodFlag::NONE);
    // if (req.w >= data.dist)
    //   *WLEmptyWork += 1;
    unsigned int v;
    while (req.w < (v = data.dist[req.c])) {
      if (__sync_bool_compare_and_swap(&data.dist[req.c], v, req.w)) {
	// if (v != DIST_INFINITY)
	//   *BadWork += 1;
	for (Graph::edge_iterator ii = graph.edge_begin(req.n, Galois::MethodFlag::NONE),
	       ee = graph.edge_end(req.n, Galois::MethodFlag::NONE); ii != ee; ++ii) {
	  GNode dst = graph.getEdgeDst(ii);
	  int d = graph.getEdgeData(ii);
	  unsigned int newDist = req.w + d;
	  SNode& rdata = graph.getData(dst,Galois::MethodFlag::NONE);
	  if (newDist < rdata.dist[req.c])
	    lwl.push(UpdateRequest(dst, newDist, req.c));
	}
	break;
      }
    }
  }
};

struct reset {
  void operator()(GNode n) {//, Galois::UserContext<GNode>& lwl) {
    SNode& S = graph.getData(n, Galois::MethodFlag::NONE);
    for (int i = 0; i < NUM; ++i)
      S.dist[i] = DIST_INFINITY;
  }
  // void operator()(GNode n, Galois::UserContext<GNode>& lwl) {
  //   operator()(n);
  // }
};

void runBodyParallel(const GNode src[NUM], int n) {
  using namespace Galois::WorkList;
  typedef dChunkedLIFO<16> dChunk;
  typedef ChunkedLIFO<16> Chunk;
  typedef OrderedByIntegerMetric<UpdateRequestIndexer,dChunk> OBIM;

  Galois::StatTimer T;

  UpdateRequest one[NUM];
  for (int i = 0; i < n; ++i)
    one[i] = UpdateRequest(src[i], 0, i);
  T.start();
  Galois::for_each(&one[0], &one[n], process(), Galois::wl<OBIM>());
  T.stop();
}

void resetParallel() {
  Galois::do_all(graph.begin(), graph.end(), reset());
}

int main(int argc, char **argv) {
  LonestarStart(argc, argv, name, desc, url);

  // Galois::Statistic<unsigned int> sBadWork("BadWork");
  // Galois::Statistic<unsigned int> sWLEmptyWork("WLEmptyWork");
  // BadWork = &sBadWork;
  // WLEmptyWork = &sWLEmptyWork;

  Galois::Graph::readGraph(graph, filename);

  std::cout << "Read " << graph.size() << " nodes\n";
  std::cout << "Using delta-step of " << (1 << stepShift) << "\n";
  std::cout << "Doing " << NUM << " at a time\n";
  std::cout << "WARNING: Performance varies considerably due to -delta.  Do not expect the default to be good for your graph\n";

  unsigned int id = 0;
  for (Graph::iterator src = graph.begin(), ee =
      graph.end(); src != ee; ++src) {
    SNode& node = graph.getData(*src,Galois::MethodFlag::NONE);
    node.id = id++;
  }

  resetParallel();

  Galois::StatTimer T("AllSourcesTimer");
  T.start();
  int at = 0;
  GNode N[NUM];
  for (Graph::iterator src = graph.begin(), ee =
	 graph.end(); src != ee; ++src) {
    N[at++] = *src;
    if (at == NUM) {
      runBodyParallel(N, NUM);
      resetParallel();
      at = 0;
    }
  }
  if (at != 0)
    runBodyParallel(N, at);
    
  T.stop();

  return 0;
}
