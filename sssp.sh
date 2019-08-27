
# GALOIS_HOME=
# SOC_DATA=./datasets
# ROAD_DATA=./datasets

THREADS=( 1 5 10 20 30 40 )
NUM_TRY=5

LOG_DIR=sssp-logs
mkdir $LOG_DIR

for t in "${THREADS[@]}"
do      
    count=0
    while [ $count -lt $NUM_TRY ] 
    do
        wl=obim
        $GALOIS_HOME/sssp/sssp  -t $t -wl $wl -delta 0 -startNode 12 $SOC_DATA/twitter40.bin > ${LOG_DIR}/twitter40_wl_${wl}_t_${t}_n_${count}
        $GALOIS_HOME/sssp/sssp  -t $t -wl $wl -delta 14 -startNode 1 $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}

        wl=spraylist
        $GALOIS_HOME/sssp/sssp  -t $t -wl $wl -delta 0 -startNode 12 $SOC_DATA/twitter40.bin > ${LOG_DIR}/twitter40_wl_${wl}_t_${t}_n_${count}
        $GALOIS_HOME/sssp/sssp  -t $t -wl $wl -delta 0 -startNode 1 $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}

        wl=multiqueue4
        $GALOIS_HOME/sssp/sssp  -t $t -wl $wl -delta 0 -startNode 12 $SOC_DATA/twitter40.bin > ${LOG_DIR}/twitter40_wl_${wl}_t_${t}_n_${count}
        $GALOIS_HOME/sssp/sssp  -t $t -wl $wl -delta 0 -startNode 1 $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}

        wl=swarm
        $GALOIS_HOME/sssp/sssp  -t $t -wl $wl -delta 0 -startNode 12 $SOC_DATA/twitter40.bin > ${LOG_DIR}/twitter40_wl_${wl}_t_${t}_n_${count}
        $GALOIS_HOME/sssp/sssp  -t $t -wl $wl -delta 0 -startNode 1 $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}

        wl=adap-obim
        $GALOIS_HOME/sssp/sssp  -t $t -wl $wl -delta 0 -startNode 12 $SOC_DATA/twitter40.bin > ${LOG_DIR}/twitter40_wl_${wl}_t_${t}_n_${count}
        $GALOIS_HOME/sssp/sssp  -t $t -wl $wl -delta 0 -startNode 1 $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}

        wl=obim
        $GALOIS_HOME/sssp/sssp  -t $t -wl $wl -delta 8 -startNode 12 $SOC_DATA/twitter40.bin > ${LOG_DIR}/twitter40_wl_${wl}d_t_${t}_n_${count}
        $GALOIS_HOME/sssp/sssp  -t $t -wl $wl -delta 8 -startNode 1 $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}d_t_${t}_n_${count}

        echo "Done ${count}"
        ((count++))
    done
    echo "Done thread ${t}"
done

