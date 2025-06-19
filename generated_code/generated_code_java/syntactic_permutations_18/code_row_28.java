public class IndexOf {
    public static void main(String[] args) {
        int[] arr = new int[10];
        for (int i=0; i<arr.length; i++) {
            arr[i] = i*2 + 5;
        }
        int index = Integer.parseInt(args[0]);
        System.out.println(arr[index-1]);
    }
}