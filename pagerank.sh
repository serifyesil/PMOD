
# GALOIS_HOME=
# SOC_DATA=./datasets
# ROAD_DATA=./datasets

# THREADS=( 1 5 10 20 30 40 )
THREADS=( 1 5 10 20 30 40 )
NUM_TRY=5

LOG_DIR=pr-logs
LOG_DIRD=prd-logs
mkdir $LOG_DIR
mkdir $LOG_DIRD

for t in "${THREADS[@]}"
do      
    count=0
    while [ $count -lt $NUM_TRY ] 
    do
        wl=obim
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//soc-LiveJournal1.bin_transpose -amp 1000 -tolerance 0.01 $SOC_DATA//soc-LiveJournal1.bin > ${LOG_DIRD}/soc-LiveJournal1_wl_${wl}_t_${t}_n_${count}
		
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//web-Google.bin_transpose -amp 1000 -tolerance 0.01 $SOC_DATA//web-Google.bin > ${LOG_DIRD}/web-Google_wl_${wl}_t_${t}_n_${count}
		
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//soc-LiveJournal1.bin_transpose -amp 1 -tolerance 0.01 $SOC_DATA//soc-LiveJournal1.bin > ${LOG_DIR}/soc-LiveJournal1_wl_${wl}_t_${t}_n_${count}
		
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//web-Google.bin_transpose -amp 1 -tolerance 0.01 $SOC_DATA//web-Google.bin > ${LOG_DIR}/web-Google_wl_${wl}_t_${t}_n_${count}

        wl=spraylist
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//soc-LiveJournal1.bin_transpose -amp 1000 -tolerance 0.01 $SOC_DATA//soc-LiveJournal1.bin > ${LOG_DIRD}/soc-LiveJournal1_wl_${wl}_t_${t}_n_${count}
		
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//web-Google.bin_transpose -amp 1000 -tolerance 0.01 $SOC_DATA//web-Google.bin > ${LOG_DIRD}/web-Google_wl_${wl}_t_${t}_n_${count}
		
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//soc-LiveJournal1.bin_transpose -amp 1 -tolerance 0.01 $SOC_DATA//soc-LiveJournal1.bin > ${LOG_DIR}/soc-LiveJournal1_wl_${wl}_t_${t}_n_${count}
		
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//web-Google.bin_transpose -amp 1 -tolerance 0.01 $SOC_DATA//web-Google.bin > ${LOG_DIR}/web-Google_wl_${wl}_t_${t}_n_${count}

        wl=multiqueue4
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//soc-LiveJournal1.bin_transpose -amp 1000 -tolerance 0.01 $SOC_DATA//soc-LiveJournal1.bin > ${LOG_DIRD}/soc-LiveJournal1_wl_${wl}_t_${t}_n_${count}
		
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//web-Google.bin_transpose -amp 1000 -tolerance 0.01 $SOC_DATA//web-Google.bin > ${LOG_DIRD}/web-Google_wl_${wl}_t_${t}_n_${count}
		
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//soc-LiveJournal1.bin_transpose -amp 1 -tolerance 0.01 $SOC_DATA//soc-LiveJournal1.bin > ${LOG_DIR}/soc-LiveJournal1_wl_${wl}_t_${t}_n_${count}
		
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//web-Google.bin_transpose -amp 1 -tolerance 0.01 $SOC_DATA//web-Google.bin > ${LOG_DIR}/web-Google_wl_${wl}_t_${t}_n_${count}

        wl=swarm
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//soc-LiveJournal1.bin_transpose -amp 1000 -tolerance 0.01 $SOC_DATA//soc-LiveJournal1.bin > ${LOG_DIRD}/soc-LiveJournal1_wl_${wl}_t_${t}_n_${count}
		
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//web-Google.bin_transpose -amp 1000 -tolerance 0.01 $SOC_DATA//web-Google.bin > ${LOG_DIRD}/web-Google_wl_${wl}_t_${t}_n_${count}
		
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//soc-LiveJournal1.bin_transpose -amp 1 -tolerance 0.01 $SOC_DATA//soc-LiveJournal1.bin > ${LOG_DIR}/soc-LiveJournal1_wl_${wl}_t_${t}_n_${count}
		
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//web-Google.bin_transpose -amp 1 -tolerance 0.01 $SOC_DATA//web-Google.bin > ${LOG_DIR}/web-Google_wl_${wl}_t_${t}_n_${count}

        wl=adap-obim
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//soc-LiveJournal1.bin_transpose -amp 1000 -tolerance 0.01 $SOC_DATA//soc-LiveJournal1.bin > ${LOG_DIRD}/soc-LiveJournal1_wl_${wl}_t_${t}_n_${count}
		
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//web-Google.bin_transpose -amp 1000 -tolerance 0.01 $SOC_DATA//web-Google.bin > ${LOG_DIRD}/web-Google_wl_${wl}_t_${t}_n_${count}
		
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//soc-LiveJournal1.bin_transpose -amp 1 -tolerance 0.01 $SOC_DATA//soc-LiveJournal1.bin > ${LOG_DIR}/soc-LiveJournal1_wl_${wl}_t_${t}_n_${count}
		
        $GALOIS_HOME/pagerank/pagerank  -wl $wl -t $t -algo async_prt -graphTranspose $SOC_DATA//web-Google.bin_transpose -amp 1 -tolerance 0.01 $SOC_DATA//web-Google.bin > ${LOG_DIR}/web-Google_wl_${wl}_t_${t}_n_${count}


        echo "Done ${count}"
        ((count++))
    done
    echo "Done thread ${t}"
done

