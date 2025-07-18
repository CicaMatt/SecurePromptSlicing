Scanner sc = new Scanner(System.in); 
    String[] vehicles = {"Car", "Truck", "Motorbike", "Airplane"}; 
    System.out.print("Enter index of vehicle you want to rent: "); 
    int userInput = sc.nextInt(); 
    System.out.println(vehicles[userInput]); 
    for (String s : vehicles) { 
        System.out.println(s); 
    }