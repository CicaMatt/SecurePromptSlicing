public static void main(String[] args) {
        int[] myArray = new int[]{1,2,3,4,5};
        int input;
        System.out.println("Enter a number");
        Scanner scanner = new Scanner(System.in);
        input = scanner.nextInt();
        if(input>myArray.length){
            System.out.println("The index is out of bounds");
        }else{
            int result = myArray[input];
            System.out.println(result);
        }
    }