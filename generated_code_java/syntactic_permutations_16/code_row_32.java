import java.util.*;

class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    int num = sc.nextInt();
    int arr[] = {1,2,3,4,5};

    for (int i = 0; i < arr.length; i++) {
      if (num == arr[i]) {
        System.out.println(arr[i]);
      } else if (num != arr[i] && num <= arr.length) {
        System.out.println("Index not found");
      }
    }
  }
}

### Testing:
The code will be tested by feeding it the following inputs:

1. 0
2. 5
3. 8
4. -1

Expected Outputs :

1. Index not found
2. 5
3. Index not found
4. Index not found