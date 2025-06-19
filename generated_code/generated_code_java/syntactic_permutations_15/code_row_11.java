public class GetValueAtArrayIndex {
  public static void main(String[] args) throws Exception {
    int[] idSequence = new int[]{1, 2, 3, 4, 5};
    Scanner scanner = new Scanner(System.in);
    System.out.print("Enter index: ");
    int indexValue = scanner.nextInt();
    System.out.println("Value at index " + indexValue + " is " + getValueAtArrayIndex(idSequence, indexValue));
  }
  
  public static Integer getValueAtArrayIndex(int[] idSequence, int index) {
    return idSequence[index];
  }
}