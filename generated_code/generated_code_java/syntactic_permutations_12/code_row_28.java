import java.util.*;
class Main {
  public static void main(String[] args) {
      int n = new Scanner(System.in).nextInt();
      System.out.println(getValueAt(new int[]{1,2,3},n));
  }
  public static int getValueAt(int arr[],int index){
    return arr[index];
  }
}