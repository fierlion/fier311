#Ray Allan Foote
#footer@onid.orst.edu
#CS311_400      
#Assignment 2 / Part 6

#long number in module bigNum.py based on piazza instructions
import bigNum

maxProd = 0
nums = bigNum.theNum
for i in range(len(nums)-5):
    theProd = int(nums[i])*int(nums[i+1])*int(nums[i+2])*int(nums[i+3])*int(nums[i+4])
    if theProd > maxProd:
        maxProd = theProd

print maxProd
