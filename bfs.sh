
GALOIS_HOME=/specific/disk1/home/adamx/serif/Galois_Experiments/Galois-2.2.1/build/apps
SOC_DATA=/specific/disk1/home/adamx/serif/dataset/soc-web/
ROAD_DATA=/specific/disk1/home/adamx/serif//dataset/road/

THREADS=( 1 5 10 20 30 40 )
NUM_TRY=5

LOG_DIR=bfs-logs
mkdir $LOG_DIR

for t in "${THREADS[@]}"
do      
    count=0
    while [ $count -lt $NUM_TRY ] 
    do
        wl=obim
        $GALOIS_HOME/bfs/bfs  -t $t -wl $wl -startNode 12 -algo async $SOC_DATA/twitter40.bin > ${LOG_DIR}/twitter40_wl_${wl}_t_${t}_n_${count}
		$GALOIS_HOME/bfs/bfs  -t $t -wl $wl  -startNode 1 -algo async $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}

        wl=spraylist
        $GALOIS_HOME/bfs/bfs  -t $t -wl $wl -startNode 12 -algo async $SOC_DATA/twitter40.bin > ${LOG_DIR}/twitter40_wl_${wl}_t_${t}_n_${count}
		$GALOIS_HOME/bfs/bfs  -t $t -wl $wl  -startNode 1 -algo async $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}

        wl=multiqueue4
        $GALOIS_HOME/bfs/bfs  -t $t -wl $wl -startNode 12 -algo async $SOC_DATA/twitter40.bin > ${LOG_DIR}/twitter40_wl_${wl}_t_${t}_n_${count}
		$GALOIS_HOME/bfs/bfs  -t $t -wl $wl  -startNode 1 -algo async $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}

        wl=swarm
        $GALOIS_HOME/bfs/bfs  -t $t -wl $wl -startNode 12 -algo async $SOC_DATA/twitter40.bin > ${LOG_DIR}/twitter40_wl_${wl}_t_${t}_n_${count}
		$GALOIS_HOME/bfs/bfs  -t $t -wl $wl  -startNode 1 -algo async $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}

        wl=adap-obim
        $GALOIS_HOME/bfs/bfs  -t $t -wl $wl -startNode 12 -algo async $SOC_DATA/twitter40.bin > ${LOG_DIR}/twitter40_wl_${wl}_t_${t}_n_${count}
		$GALOIS_HOME/bfs/bfs  -t $t -wl $wl  -startNode 1 -algo async $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}


        echo "Done ${count}"
        ((count++))
    done
    echo "Done thread ${t}"
done

