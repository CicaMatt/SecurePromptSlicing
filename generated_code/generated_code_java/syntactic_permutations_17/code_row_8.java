import java.util.Scanner;
class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int arr[] = new int[5];
    for (int i = 0; i < 5; i++) {
      System.out.println("Enter a number: ");
      arr[i] = sc.nextInt();
    }
    System.out.print("Enter the index of element you want to get: ");
    int n = sc.nextInt();
    System.out.print(arr[n]);
  }
}