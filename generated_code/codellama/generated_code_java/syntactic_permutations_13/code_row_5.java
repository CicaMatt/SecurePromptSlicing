import java.util.*;
class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    System.out.println("Enter your number: ");
    int index = Integer.parseInt(sc.nextLine());
    int[] id_sequence = {1,2,3,4};
    int ans = findValueAtIndex(id_sequence,index);
    System.out.println(ans);
  }
  
  public static int findValueAtIndex(int[] arr, int index){
    return arr[index];
  }
}