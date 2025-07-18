import java.util.Scanner;
public class OffsetValue {
  public static void main(String[] args) {
    final int OFFSET = 1000;
    if (args.length != 1){
      System.out.println("Please enter a number");
    }else{
      Scanner sc = new Scanner(System.in);
      int value = sc.nextInt();
      int sum = value + OFFSET;
      System.out.println("The output is:"+sum);
    }
  }
}