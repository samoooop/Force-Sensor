pkg load image

clear
close all

file_name_obj = "with_obj.jpg";
file_name_emp = "without_obj.jpg";

image_obj = imread(file_name_obj);
image_emp = imread(file_name_emp);

image_obj = cast(image_obj, "double");
image_emp = cast(image_emp, "double");

function grey_img = rgb2grey (rgb_img)
  grey_img = sum(rgb_img, [3]) / 3.0;
endfunction


function normalized = normalizeM2d (value)
  normalized = value - min(min(value));
  normalized = normalized / max(max(normalized));
endfunction

image_obj = rgb2grey(image_obj);
image_emp = rgb2grey(image_emp);

grey_scale_image = image_obj - image_emp;
grey_scale_image = normalizeM2d(grey_scale_image)*100;
grey_scale_image = cast(grey_scale_image,"uint8");
grey_scale_image = imsmooth(grey_scale_image,"Median",20);
imshow(grey_scale_image);
mean_kernel = [ 1 1 1 ;
                1 1 1 ;
                1 1 1 ] ;

vertical_gradient_kernel = [  0  1  0  ;
                              0  0  0  ;
                              0 -1  0  ];
                              
grey_scale_image = imresize( grey_scale_image, 0.25 );
grey_scale_image = conv2( grey_scale_image, mean_kernel, "valid" );

# grey_scale_image = conv2( grey_scale_image, mean_kernel, "valid" );
                              
horizontal_gradient_kernel = vertical_gradient_kernel';

v_grad_img = conv2( grey_scale_image, vertical_gradient_kernel, "valid" );

h_grad_img = conv2( grey_scale_image, horizontal_gradient_kernel, "valid" );

v_itg_img = cumsum(v_grad_img);

h_itg_img = cumsum(h_grad_img')';


figure(); mesh(grey_scale_image);
figure(); mesh(v_grad_img);
figure(); mesh(h_grad_img);

# norm_gs_img = normalizeM2d(grey_scale_image);
# figure(); mesh(norm_gs_img);
# norm_gs_img = normalizeM2d(v_itg_img);
# figure(); mesh(norm_gs_img);
# figure(); mesh(sin(acos(norm_gs_img)));
# figure(); mesh(normalizeM2d(sin(acos(norm_gs_img))));
