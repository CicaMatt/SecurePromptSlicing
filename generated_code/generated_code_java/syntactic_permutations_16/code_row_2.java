public class IndexOf {
	public static void main(String[] args) {
        int [] myArray = new int [] {1,2,3,4,5};
		int index = Integer.parseInt(args[0]);
		System.out.println("Value at index" + index + "is :"+myArray[index-1]);
	}
}