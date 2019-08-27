
GALOIS_HOME=/specific/disk1/home/adamx/serif/Galois_Experiments/Galois-2.2.1/build/apps
SOC_DATA=/specific/disk1/home/adamx/serif/dataset/soc-web/
ROAD_DATA=/specific/disk1/home/adamx/serif//dataset/road/

THREADS=( 1 5 10 20 30 40 )
NUM_TRY=5

LOG_DIR=astar-logs
mkdir $LOG_DIR

for t in "${THREADS[@]}"
do      
    count=0
    while [ $count -lt $NUM_TRY ] 
    do
        wl=obim
        $GALOIS_HOME/astar/astar  -t $t -wl $wl -delta 14 -startNode 1 -destNode 22629042 -reportNode 22629042 -coordFilename $ROAD_DATA/USA-road-dUSA.co $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}
        $GALOIS_HOME/astar/astar -t $t -wl $wl -delta 14 -startNode 1 -destNode 5639706  -reportNode 5639706  -coordFilename $ROAD_DATA/USA-road-dW.co $ROAD_DATA/USA-road-dW.bin > ${LOG_DIR}/USA-road-dW_wl_${wl}_t_${t}_n_${count}

        wl=spraylist
        $GALOIS_HOME/astar/astar -t $t -wl $wl -delta 0 -startNode 1 -destNode 22629042 -reportNode 22629042 -coordFilename $ROAD_DATA/USA-road-dUSA.co $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}
		$GALOIS_HOME/astar/astar -t $t -wl $wl -delta 0 -startNode 1 -destNode 5639706  -reportNode 5639706  -coordFilename $ROAD_DATA/USA-road-dW.co $ROAD_DATA/USA-road-dW.bin > ${LOG_DIR}/USA-road-dW_wl_${wl}_t_${t}_n_${count}

        wl=multiqueue4
        $GALOIS_HOME/astar/astar -t $t -wl $wl -delta 0 -startNode 1 -destNode 22629042 -reportNode 22629042 -coordFilename $ROAD_DATA/USA-road-dUSA.co $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}
		$GALOIS_HOME/astar/astar -t $t -wl $wl -delta 0 -startNode 1 -destNode 5639706  -reportNode 5639706  -coordFilename $ROAD_DATA/USA-road-dW.co $ROAD_DATA/USA-road-dW.bin > ${LOG_DIR}/USA-road-dW_wl_${wl}_t_${t}_n_${count}

        wl=swarm
        $GALOIS_HOME/astar/astar -t $t -wl $wl -delta 0 -startNode 1 -destNode 22629042 -reportNode 22629042 -coordFilename $ROAD_DATA/USA-road-dUSA.co $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}
		$GALOIS_HOME/astar/astar -t $t -wl $wl -delta 0 -startNode 1 -destNode 5639706  -reportNode 5639706  -coordFilename $ROAD_DATA/USA-road-dW.co $ROAD_DATA/USA-road-dW.bin > ${LOG_DIR}/USA-road-dW_wl_${wl}_t_${t}_n_${count}

        wl=adap-obim
        $GALOIS_HOME/astar/astar -t $t -wl $wl -delta 0 -startNode 1 -destNode 22629042 -reportNode 22629042 -coordFilename $ROAD_DATA/USA-road-dUSA.co $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}
		$GALOIS_HOME/astar/astar -t $t -wl $wl -delta 0 -startNode 1 -destNode 5639706  -reportNode 5639706  -coordFilename $ROAD_DATA/USA-road-dW.co $ROAD_DATA/USA-road-dW.bin > ${LOG_DIR}/USA-road-dW_wl_${wl}_t_${t}_n_${count}

        wl=obim
        $GALOIS_HOME/astar/astar -t $t -wl $wl -delta 8 -startNode 1 -destNode 22629042 -reportNode 22629042 -coordFilename $ROAD_DATA/USA-road-dUSA.co $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_obimd_t_${t}_n_${count}
		$GALOIS_HOME/astar/astar -t $t -wl $wl -delta 8 -startNode 1 -destNode 5639706  -reportNode 5639706  -coordFilename $ROAD_DATA/USA-road-dW.co $ROAD_DATA/USA-road-dW.bin > ${LOG_DIR}/USA-road-dW_wl_obimd_t_${t}_n_${count}

        echo "Done ${count}"
        ((count++))
    done
    echo "Done thread ${t}"
done

