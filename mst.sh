
# GALOIS_HOME=
# SOC_DATA=./datasets
# ROAD_DATA=./datasets

# 1 5 10 20 30
THREADS=( 1 5 10 20 30 40 )
NUM_TRY=5

LOG_DIR=mst-logs
mkdir $LOG_DIR

for t in "${THREADS[@]}"
do      
    count=0
    while [ $count -lt $NUM_TRY ] 
    do
        wl=obim
        $GALOIS_HOME/boruvka/boruvka-merge -t $t -wl $wl $ROAD_DATA/USA-road-dW.bin > ${LOG_DIR}/USA-road-dW_wl_${wl}_t_${t}_n_${count}	
        $GALOIS_HOME/boruvka/boruvka-merge -t $t -wl $wl $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}

        wl=spraylist
        $GALOIS_HOME/boruvka/boruvka-merge -t $t -wl $wl $ROAD_DATA/USA-road-dW.bin > ${LOG_DIR}/USA-road-dW_wl_${wl}_t_${t}_n_${count}
        $GALOIS_HOME/boruvka/boruvka-merge -t $t -wl $wl $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}

        wl=multiqueue4
        $GALOIS_HOME/boruvka/boruvka-merge -t $t -wl $wl $ROAD_DATA/USA-road-dW.bin > ${LOG_DIR}/USA-road-dW_wl_${wl}_t_${t}_n_${count}
		$GALOIS_HOME/boruvka/boruvka-merge -t $t -wl $wl $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}

        wl=swarm
        $GALOIS_HOME/boruvka/boruvka-merge -t $t -wl $wl $ROAD_DATA/USA-road-dW.bin > ${LOG_DIR}/USA-road-dW_wl_${wl}_t_${t}_n_${count}
		$GALOIS_HOME/boruvka/boruvka-merge -t $t -wl $wl $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}

        wl=adap-obim
        $GALOIS_HOME/boruvka/boruvka-merge -t $t -wl $wl $ROAD_DATA/USA-road-dW.bin > ${LOG_DIR}/USA-road-dW_wl_${wl}_t_${t}_n_${count}
		$GALOIS_HOME/boruvka/boruvka-merge -t $t -wl $wl $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR}/USA-road-dUSA_wl_${wl}_t_${t}_n_${count}


        echo "Done ${count}"
        ((count++))
    done
    echo "Done thread ${t}"
done

