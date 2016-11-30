function [H] = getGauBlurH(Y_SIZE,X_SIZE,SIGMA)
  % N is grid size, sigma speaks for itself
[x y] = meshgrid(1:X_SIZE,1:Y_SIZE);
mid_x = X_SIZE/2;
mid_y = Y_SIZE/2;
H = exp(-(x-mid_x).^2/(2*SIGMA^2)-(y-mid_y).^2/(2*SIGMA^2));
%H = H./sum(H(:));
%imshow(H)
end