#include  <internal_volume_io.h>
#include  <numerical.h>
#include  <prog_utils.h>

#define  LSQ_TYPE      float
#define  MINIMIZE_LSQ  minimize_lsq

#include  "minimize_lsq_include.c"

public  Real   minimize_lsq_float(
    int              n_parameters,
    int              n_equations,
    int              n_nodes_per_equation[],
    int              *node_list[],
    float            constants[],
    float            *node_weights[],
    int              n_iters,
    Real             node_values[] )
{
    return( private_minimize_lsq( n_parameters, n_equations,
                                  n_nodes_per_equation, node_list,
                                  constants, node_weights, n_iters,
                                  node_values ) );
}