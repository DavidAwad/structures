#!/usr/bin/env ruby
puts "Enter the string you want to search "
input = gets.chomp

char_hash = input.each_char.with_object(Hash.new(0)) { |i, h| h[i] += 1 }

goc = "" 
max = 0 

char_hash.each do |key,value| 
  if value > max then
    max = value
    goc = key
  end
end


puts "The character #{goc} occurs the most frequently"
