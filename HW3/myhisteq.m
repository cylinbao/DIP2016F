function [output] = myhisteq(input)

count = imhist(input);
pdf = count/sum(count);

cdf(1) = pdf(1);
for i = 2:size(count)
    cdf(i) = cdf(i-1) + pdf(i); 
end

output = arrayfun(@(x) uint8(255*cdf(x+1)), input);

end