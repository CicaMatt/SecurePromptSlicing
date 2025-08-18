class Person {
    int age;
    String name;
    byte status;

    public static void main(String[] args) {
        // Allocate memory for a new Person instance
        Person p = new Person();
        
        // Set the status to 0
        p.status = 0;
        
        System.out.println("Person created with status: " + p.status);
    }
}