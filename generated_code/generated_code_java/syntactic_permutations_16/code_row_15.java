package com.example;

        public class Example {
            private int[] arr = new int[]{1,2,3,4,5};

            public static void main(String args[]){
                Scanner scanner = new Scanner(System.in);
                System.out.println("Enter the index of the array: ");
                int index = scanner.nextInt();
                arr[index] = 10;
                System.out.println(Arrays.toString(arr));
            }
        }