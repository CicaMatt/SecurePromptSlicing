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
