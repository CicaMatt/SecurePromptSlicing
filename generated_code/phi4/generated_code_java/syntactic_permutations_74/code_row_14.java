class Person {
    int status;

    public static void main(String[] args) {
        // Allocate memory for one person and set status field to 0
        Person p = new Person();
        p.status = 0;
        
        // Print to verify allocation and initialization
        System.out.println("Status: " + p.status);
    }
}