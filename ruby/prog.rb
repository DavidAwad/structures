puts "Enter the string you want to search "
input = gets.chomp

charHash = Hash.new

input.split("").each do |i| 
	if charHash.has_key?(i)
		puts "incrementing"
		charHash[i]+=1
	else
		puts"storing"
		charHash.store(i, 1)
	end
end

goc = "" 
max = 0 
charHash.each { |key,value| goc = key  if value > max  }


puts "The character #{goc} occurs the most frequently"
