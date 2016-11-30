function [gb] = myimgaussfilt(img,SIGMA)

img = double(img);
r = img(:,:,1);
g = img(:,:,2);
b = img(:,:,3);
[img_x img_y img_z] = size(img);

%SIGMA = 50;
H = getGauBlurH(img_x,img_y,SIGMA);

fr = fftshift(fft2(r)) .* H;
fg = fftshift(fft2(g)) .* H;
fb = fftshift(fft2(b)) .* H;

% fr = fft2(r) .* F;
% fg = fft2(g) .* F;
% fb = fft2(b) .* F;

ifr = ifftshift(fr);
ifg = ifftshift(fg);
ifb = ifftshift(fb);

% ir = fftshift(real(ifft2(ifr)));
% ig = fftshift(real(ifft2(ifg)));
% ib = fftshift(real(ifft2(ifb)));

ir = real(ifft2(ifr));
ig = real(ifft2(ifg));
ib = real(ifft2(ifb));

gb = uint8(cat(3,ir,ig,ib));
end
