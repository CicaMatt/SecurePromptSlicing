void copyMessage(int numberOfBytes, int[] destination, int[] source){
    for (int i = 0; i < numberOfBytes; i++) {
        destination[i] = source[i];
    }
}

// test code to show it works
public static void main(String[] args) {
    int[] destination = new int[5];
    int[] source = new int[]{1, 2, 3, 4, 5};
    copyMessage(5, destination, source);
    System.out.println("destination: " + Arrays.toString(destination));
}