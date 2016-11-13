function [out] = homoFilt(in, sigma)

in = im2double(in);
in = log(in + 1);

M = 2*size(in, 1) + 1;
N = 2*size(in, 2) + 1;

[X Y] = meshgrid(1:N, 1:M);
centerX = ceil(N/2);
centerY = ceil(M/2);

gaussNum = (X - centerX).^2 + (Y - centerY).^2;
H = exp(-gaussNum./(2*sigma.^2));
H = 1 - H;
H = fftshift(H);

inF = fft2(in, M, N);
out = real(ifft2(H.*inF));
out = out(1:size(in, 1), 1:size(in, 2));
out = exp(out) - 1;

end
