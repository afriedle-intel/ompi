  /*
 * Copyright (c) 2013      Mellanox Technologies, Inc.
 *                         All rights reserved.
 * Copyright (c) 2013 Cisco Systems, Inc.  All rights reserved.
 * $COPYRIGHT$
 * 
 * Additional copyrights may follow
 * 
 * $HEADER$	
 */

#include "oshmem_config.h"
#include "oshmem/shmem/fortran/bindings.h"
#include "oshmem/include/shmem.h"
#include "oshmem/shmem/shmem_api_logger.h"
#include "oshmem/runtime/runtime.h"
#include "oshmem/mca/spml/spml.h"
#include "ompi/datatype/ompi_datatype.h"
#include "stdio.h"

OMPI_GENERATE_FORTRAN_BINDINGS (void,
        SHMEM_LOGICAL_IPUT,
        shmem_logical_iput_,
        shmem_logical_iput__,
        shmem_logical_iput_f,
        (FORTRAN_POINTER_T target, FORTRAN_POINTER_T source, MPI_Fint *tst, MPI_Fint *sst, MPI_Fint *len, MPI_Fint *pe), 
        (target,source,tst,sst,len,pe) )

void shmem_logical_iput_f(FORTRAN_POINTER_T target, FORTRAN_POINTER_T source, MPI_Fint *tst, MPI_Fint *sst, MPI_Fint *len, MPI_Fint *pe)
{
    int i;
    int length = OMPI_FINT_2_INT(*len);
    int tst_c = OMPI_FINT_2_INT(*tst);
    int sst_c = OMPI_FINT_2_INT(*sst);

    size_t logical_type_size = 0;
    ompi_datatype_type_size(&ompi_mpi_logical.dt, &logical_type_size);

    for (i=0; i<length; i++)
    {  
        MCA_SPML_CALL(put((uint8_t*)FPTR_2_VOID_PTR(target) + i * tst_c * logical_type_size, 
            logical_type_size, 
            (uint8_t*)FPTR_2_VOID_PTR(source) + i * sst_c * logical_type_size, 
            OMPI_FINT_2_INT(*pe)));

    }
}
