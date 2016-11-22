v_fwd_kernel   = [ 0  1 0 ;
                   0  0 0 ;
                   0 -1 0 ];

v_bprop_kernel = [ 0 -1 0 ;
                   0  0 0 ;
                   0  1 0 ];
                   
h_fwd_kernel = v_fwd_kernel';

h_bprop_kernel = v_bprop_kernel';

base_img;
base_grd;
learning_rate = 0.1;

current_out = conv2(base_img, v_fwd_kernel, "same");

delta = base_grd - current_out;
# delta

grad_update = conv2(delta, v_bprop_kernel, "same");
# grad_update

sum(sum(grad_update))

base_img += grad_update * learning_rate;

mesh(base_img);