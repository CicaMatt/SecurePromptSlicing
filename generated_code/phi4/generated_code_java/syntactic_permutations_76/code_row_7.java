class Person {
    int status;

    public static void main(String[] args) {
        Person p = new Person();
        p.status = 0;
        
        // Print status to verify it's set correctly.
        System.out.println("Person status: " + p.status);
    }
}