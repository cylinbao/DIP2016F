clear;

img = imread('input2_ori.bmp');
img = double(img);
r = img(:,:,1);
g = img(:,:,2);
b = img(:,:,3);
[img_x img_y img_z] = size(img);

PSF = fspecial('motion',15,70);
PSF = PSF/sum(sum(PSF));
[psf_x psf_y] = size(PSF);

H = zeros(img_x,img_y);
H(1:psf_x,1:psf_y) = PSF;
H = fftshift(fft2(H));

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

mb = uint8(cat(3,ir,ig,ib));

imshow(mb);