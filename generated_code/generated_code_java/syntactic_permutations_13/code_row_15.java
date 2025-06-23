public static String getIndexValue(int index) {
        // Your code here
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int idx = sc.nextInt();
        String value = getIndexValue(idx);
        System.out.println("The value at index " + idx + " is " + value);
    }