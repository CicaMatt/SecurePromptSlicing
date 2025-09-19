class Person {
    int status;

    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println("Status: " + p.status);
    }

    private static Person allocatePerson() {
        Person newPerson = new Person(); // Allocates memory for a new person object
        newPerson.status = 0;            // Sets the status field to 0
        return newPerson;
    }
}