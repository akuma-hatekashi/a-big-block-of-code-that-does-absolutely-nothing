lambda arguments: expression
def squares(num):
    square = num * num 
    # You can also write square = num ** 2
    return square
    
squares(5)
f = lambda x:x**2
f(5)
def even(a):
    new_list = []
    for i in a:
        if i%2 == 0:
            new_list.append(i)
    return(new_list)
    
a = [1,2,3,4,5]
even(a)
def square(a):
    new_list = []
    for i in a:
        i = i*i
        new_list.append(i)
    return(new_list)
    
a = [1,2,3,4,5]
square(a)
a = [1, 2, 3, 4, 5]
squares = list(map(lambda x: x ** 2, a))
print(squares)
def prod(a):
    product = 1
    for i in a:
        product = product*i
    return product

a = [1,2,3,4,5]
prod(a)
from functools import reduce

a = [1, 2, 3, 4, 5]
product = reduce(lambda x, y: x*y, a)
print(product)
print('hello world') very advanced
1,000+ Python Practice Challenges // Edabit
go to : https://edabit.com/challenges/python3
# Sample Python Program to Print Hello World

print("Hello World")
# Sample Python Program to Print Message

str = input("Welcome to Tutorial Gateway")
print(str)
# Simple Python program to Add Two Numbers

number1 = input(" Please Enter the First Number: ")
number2 = input(" Please Enter the second number: ")

# Using arithmetic + Operator to add two numbers
sum = float(number1) + float(number2)
print('The sum of {0} and {1} is {2}'.format(number1, number2, sum))
number1 = input(" Please Enter the First Number: ")
number2 = input(" Please Enter the second number: ")
sum = float(number1) + float(number2)
# Simple Python program to Add Two Numbers

number1 = float(input(" Please Enter the First Number: "))
number2 = float(input(" Please Enter the second number: "))

# Using arithmetic + Operator to add two numbers
sum = number1 + number2
print('The sum of {0} and {1} is {2}'.format(number1, number2, sum))
# Python Program to Perform Arithmetic Operations

num1 = float(input(" Please Enter the First Value Number 1: "))
num2 = float(input(" Please Enter the Second Value Number 2: "))

# Add Two Numbers
add = num1 + num2

# Subtracting num2 from num1
sub = num1 - num2

# Multiply num1 with num2
multi = num1 * num2

# Divide num1 by num2
div = num1 / num2

# Modulus of num1 and num2
mod = num1 % num2

# Exponent of num1 and num2
expo = num1 ** num2

print("The Sum of {0} and {1} = {2}".format(num1, num2, add))
print("The Subtraction of {0} from {1} = {2}".format(num2, num1, sub))
print("The Multiplication of {0} and {1} = {2}".format(num1, num2, multi))
print("The Division of {0} and {1} = {2}".format(num1, num2, div))
print("The Modulus of {0} and {1} = {2}".format(num1, num2, mod))
print("The Exponent Value of {0} and {1} = {2}".format(num1, num2, expo))
# Python Calendar Example

# import calendar module
import calendar

# ask of month and year
year = int(input("Please Enter the year Number: "))
month = int(input("Please Enter the month Number: "))

# Displaying the Python calendar
print(calendar.month(year, month))
# Python Program to Calculate Cube of a Number

number = float(input(" Please Enter any numeric Value : "))

cube = number * number * number

print("The Cube of a Given Number {0}  = {1}".format(number, cube))
# Python Program to Calculate Cube of a Number

number = float(input(" Please Enter any numeric Value : "))

cube = number ** 3

print("The Cube of a Given Number {0}  = {1}".format(number, cube))
# Python Program to Calculate Cube of a Number

def cube(num):
    return num * num * num

number = float(input(" Please Enter any numeric Value : "))

cub = cube(number)

print("The Cube of a Given Number {0}  = {1}".format(number, cub))
