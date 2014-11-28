puts "Enter the string you want to search "
input = gets.chomp

char_hash = input.each_char.with_object(Hash.new(0)) { |i, h| h[i] += 1 }

goc = "" 
max = 0 
char_hash.each { |key,value| goc = key  if value > max  }

puts "The character #{goc} occurs the most frequently"
