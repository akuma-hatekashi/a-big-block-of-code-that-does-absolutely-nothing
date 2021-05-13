public class HelloWorld
{
	public static void main(String[] args) {
		System.out.println("Hello World!");
	}
}

public class CallingMethodsInSameClass
{
	public static void main(String[] args) {
		printOne();
		printOne();
		printTwo();
	}

	public static void printOne() {
		System.out.println("Hello World");
	}

	public static void printTwo() {
		printOne();
		printOne();
	}
}
public class Factorial
{
	public static void main(String[] args)
	{	final int NUM_FACTS = 100;
		for(int i = 0; i < NUM_FACTS; i++)
			System.out.println( i + "! is " + factorial(i));
	}
	
	public static int factorial(int n)
	{	int result = 1;
		for(int i = 2; i <= n; i++)
			result *= i;
		return result;
	}
}
public class EnhancedFor
{
	public static void main(String[] args)
	{	int[] list ={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		int sum = sumListEnhanced(list);
		System.out.println("Sum of elements in list: " + sum);

		System.out.println("Original List");
		printList(list);
		System.out.println("Calling addOne");
		addOne(list);
		System.out.println("List after call to addOne");
		printList(list);
		System.out.println("Calling addOneError");
		addOneError(list);
		System.out.println("List after call to addOneError. Note elements of list did not change.");
		printList(list);
	}

	// pre: list != null
	// post: return sum of elements
	// uses enhanced for loop
	public static int sumListEnhanced(int[] list)
	{	int total = 0;
		for(int val : list)
		{	total += val;
		}
		return total;
	}

	// pre: list != null
	// post: return sum of elements
	// use traditional for loop
	public static int sumListOld(int[] list)
	{	int total = 0;
		for(int i = 0; i < list.length; i++)
		{	total += list[i];
			System.out.println( list[i] );
		}
		return total;
	}

	// pre: list != null
	// post: none.
	// The code appears to add one to every element in the list, but does not
	public static void addOneError(int[] list)
	{	for(int val : list)
		{	val = val + 1;
		}
	}

	// pre: list != null
	// post: adds one to every element of list
	public static void addOne(int[] list)
	{	for(int i = 0; i < list.length; i++)
		{	list[i]++;
		}
	}

	public static void printList(int[] list)
	{	System.out.println("index, value");
		for(int i = 0; i < list.length; i++)
		{	System.out.println(i + ", " + list[i]);
		}
	}



}
public class PrimitiveParameters
{	
	public static void main(String[] args)
	{	go();
	}
	
	public static void go()
	{	int x = 3;
		int y = 2;
		System.out.println("In method go. x: " + x + " y: " + y);
		falseSwap(x,y);
		System.out.println("in method go. x: " + x + " y: " + y);
		moreParameters(x,y);
		System.out.println("in method go. x: " + x + " y: " + y);
	}
	
	public static void falseSwap(int x, int y)
	{	System.out.println("in method falseSwap. x: " + x + " y: " + y);
		int temp = x;
		x = y;
		y = temp;
		System.out.println("in method falseSwap. x: " + x + " y: " + y);
	}
	
	public static void moreParameters(int a, int b)
	{	System.out.println("in method moreParameters. a: " + a + " b: " + b);
		a = a * b;
		b = 12;
		System.out.println("in method moreParameters. a: " + a + " b: " + b);
		falseSwap(b,a);
		System.out.println("in method moreParameters. a: " + a + " b: " + b);	
	}
}
public class StringExample
{	public static void main(String[] args)
	{	String s1 = "Computer Science";
		int x = 307;
		String s2 = s1 + " " + x;
		String s3 = s2.substring(10,17);
		String s4 = "is fun";
		String s5 = s2 + s4;
		
		System.out.println("s1: " + s1);
		System.out.println("s2: " + s2);
		System.out.println("s3: " + s3);
		System.out.println("s4: " + s4);
		System.out.println("s5: " + s5);
		
		//showing effect of precedence
		
		x = 3;
		int y = 5;
		String s6 = x + y + "total";
		String s7 = "total " + x + y;
		String s8 = " " + x + y + "total";
		System.out.println("s6: " + s6);
		System.out.println("s7: " + s7);
		System.out.println("s8: " + s8);
	}
}
