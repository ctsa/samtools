
#include "sam.h"

#include <assert.h>
#include <stdio.h>


hts_itr_t* _hitr = NULL;
samfile_t* _bfp = NULL;
hts_idx_t* _hidx = NULL;

bam1_t* _bp = NULL;



void
run_region(int ref, int beg, int end) {
    int ret;

    if (NULL != _hitr) hts_itr_destroy(_hitr);

    fprintf(stderr,"calling query: %i %i %i\n",ref,beg,end);
    _hitr = sam_itr_queryi(_hidx,ref,beg,end);
    assert(_hitr);

    while (1) { 
       ret = sam_itr_next(_bfp->file, _hitr, _bp);
       if (ret < 0) break;
    }
}


void main() {

    //char* filename = "/illumina/scratch/TUNE/data/NA12878/PG_Isaac_02.14/NA12878_S1.cram";
    char* filename = "reproduce_cram_iter_bug.cram";

    _bfp = samopen(filename, "rb", 0);
    assert(_bfp);
    _hidx = sam_index_load(_bfp, filename);
    assert(_hidx);

    _bp = bam_init1();
    assert(_bp);


    run_region(1,8872,16371);
    run_region(11,49883275,49883869);
    run_region(1,8872,16371);
}
