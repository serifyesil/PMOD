
# GALOIS_HOME=
# SOC_DATA=./datasets
# ROAD_DATA=./datasets

# 1 5 10 20 30 4
THREADS=( 40 )
NUM_TRY=5

DELTAS=( 10 12 14 16 18 )

LOG_DIR_SSSP=sssp-delta-logs
LOG_DIR_ASTAR=astar-delta-logs
mkdir $LOG_DIR_SSSP
mkdir $LOG_DIR_ASTAR

for d in "${DELTAS[@]}"
do
    for t in "${THREADS[@]}"
    do      
        count=0
        while [ $count -lt $NUM_TRY ] 
        do
            wl=obim
            
            $GALOIS_HOME/sssp/sssp  -t $t -wl $wl -delta $d -startNode 1 $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR_SSSP}/USA-road-dUSA_wl_${wl}_d_${d}_t_${t}_n_${count}

            $GALOIS_HOME/astar/astar  -t $t -wl $wl -delta $d -startNode 1 -destNode 22629042 -reportNode 22629042 -coordFilename $ROAD_DATA/USA-road-dUSA.co $ROAD_DATA/USA-road-dUSA.bin > ${LOG_DIR_ASTAR}/USA-road-dUSA_wl_${wl}_d_${d}_t_${t}_n_${count}

            echo "Done ${count}"
            ((count++))
        done
        echo "Done thread ${t}"
    done
done




DELTAS=( 4 6 8 10 12 14 )
for d in "${DELTAS[@]}"
do
    for t in "${THREADS[@]}"
    do      
        count=0
        while [ $count -lt $NUM_TRY ] 
        do
            wl=obim
            
            $GALOIS_HOME/sssp/sssp  -t $t -wl $wl -delta $d -startNode 1 ${ROAD_DATA}_64/USA-road-dUSA.bin > ${LOG_DIR_SSSP}/USA-road-dUSA64_wl_${wl}_d_${d}_t_${t}_n_${count}

            $GALOIS_HOME/sssp/sssp  -t $t -wl $wl -delta $d -startNode 1 ${ROAD_DATA}_64/USA-road-dW.bin > ${LOG_DIR_SSSP}/USA-road-dW64_wl_${wl}_d_${d}_t_${t}_n_${count}

            echo "Done ${count}"
            ((count++))
        done
        echo "Done thread ${t}"
    done
    echo "Done delta ${d}"
done