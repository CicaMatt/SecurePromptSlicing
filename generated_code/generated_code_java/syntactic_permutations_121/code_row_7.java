import java.util.Arrays;

class Main {
  public static void main(String[] args) {
    int[] myFirstIntArray = new int[5];
    for (int i = 0; i < myFirstIntArray.length; i++) {
      myFirstIntArray[i] = i;
    }
    
    int[] mySecondIntArray = Arrays.copyOf(myFirstIntArray, myFirstIntArray.length);
    
    for (int i = 0; i < mySecondIntArray.length; i++) {
      System.out.println("Element at index " + i + " in second array is: " + mySecondIntArray[i]);
    }
    
    myFirstIntArray = null;
    
    for (int i = 0; i < mySecondIntArray.length; i++) {
      System.out.println("Element at index " + i + " in second array is: " + mySecondIntArray[i]);
    }
    
    mySecondIntArray = null;
  }}