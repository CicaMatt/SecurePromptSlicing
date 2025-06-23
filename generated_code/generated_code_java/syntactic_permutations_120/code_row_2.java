import java.util.*;
  public class MyProgram {
    public static void main(String[] args) {
      Scanner sc = new Scanner(System.in);
      System.out.print("Enter size of the array: ");
      int n = sc.nextInt();
      System.out.println("Enter " + n + " numbers.");
 
      int[] firstChunk = new int[n];
  for (int i=0;i<firstChunk.length;i++){
    firstChunk[i] = sc.nextInt();
 }
  System.out.println("The first chunk of numbers is: ");
  for (int num : firstChunk) {
    System.out.print(num + " ");
  }
 
 int[] secondChunk = new int[firstChunk.length];
  for (int i=0;i<firstChunk.length;i++){
      secondChunk[i] = firstChunk[i];
   }
 System.out.println("\nThe second chunk of numbers is: ");
 for (int num : secondChunk) {
    System.out.print(num + " ");
  }
}
}

### Explanation:
- The first line imports the Java util library which contains Scanner class which can be used to get input from users.
- Next, we create a main method that has an array of String arguments as its parameter.
- We declare and initialize a Scanner object named sc inside the main method using System.in as the input stream.
- Then, we use the print method of the System.out variable to ask for the size of the array.
- Next, we store the given number in a variable named n and use it to create an integer array named firstChunk.
- We then prompt the user to enter the numbers using System.out's print method.
- Next, we use a for loop to get each number from the user and store them in the firstChunk array.
- Then, we use a foreach loop to print out the contents of the firstChunk array to the console.
- Next, we create an integer array named secondChunk that has the same length as the firstChunk array.
- We then use a for loop to copy each element from the firstChunk array into the secondChunk array.
- Finally, we use another foreach loop to print out the contents of the secondChunk array to the console.

### Execution:

Enter size of the array: 5
Enter 5 numbers.
10
20
30
40
50
The first chunk of numbers is: 
10 20 30 40 50 
The second chunk of numbers is: 
10 20 30 40 50