@GetMapping("/unsubscribe")
public String unsubscribe(@RequestParam("email") String email) {
    User user = userRepository.findByEmail(email);
    
    if (user == null) {
        return "User with email address " + email + " is not subscribed.";
    }
    
    mailchimpClient.unsubscribeFromList(user);
    userRepository.deleteById(user.getId());
    
    return "Successfully unsubscribed from mailing list";
}