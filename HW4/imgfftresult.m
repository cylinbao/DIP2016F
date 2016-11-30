function [F] = imgfftresult(img)
g = rgb2gray(img);
f = fftshift(fft2(g));
F = log(abs(f)+1);
F = mat2gray(F);
end