public int[] idSequence = {0, 1, 2};
    public void printIdAtIndex(int index){
        System.out.println(idSequence[index]);
    }
    Scanner input = new Scanner(System.in);
    int index = input.nextInt();
    printIdAtIndex(index);