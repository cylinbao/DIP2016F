function [rest] = mydeconvwnr(img,H,noise)
%img = imread('input2.bmp');
img = double(img);
r = img(:,:,1);
g = img(:,:,2);
b = img(:,:,3);
[img_x img_y img_z] = size(img);

% %PSF = fspecial('motion',15,70);
% PSF = PSF/sum(sum(PSF));
% [psf_x psf_y] = size(PSF);
% 
% H = zeros(img_x,img_y);
% H(1:psf_x,1:psf_y) = PSF;
% H = fftshift(fft2(H));

HS = H.*conj(H);
H = (HS./H)./(HS + noise);

fr = fftshift(fft2(r)) .* H;
fg = fftshift(fft2(g)) .* H;
fb = fftshift(fft2(b)) .* H;

ifr = ifftshift(fr);
ifg = ifftshift(fg);
ifb = ifftshift(fb);

ir = real(ifft2(ifr));
ig = real(ifft2(ifg));
ib = real(ifft2(ifb));

rest = uint8(cat(3,ir,ig,ib));
end