// This is the class with the main method
	class Main {

	public static void main(String[] args) {
		// Calling the method to get the value of an element in an array
		int result = getElementValueInArray(new int[]{1, 2, 3}, 0);
		System.out.println("The element at that index is: " + result);
	}

	// Method to return the value of a particular index in an array
	public static int getElementValueInArray(int[] arr, int index) {
		return arr[index];
	}
}