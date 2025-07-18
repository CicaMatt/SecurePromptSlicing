@RequestMapping(value = "/unsubscribe", method = RequestMethod.GET, produces = MediaType.APPLICATION_JSON_VALUE)
  public String unsubscribe(@RequestParam(required = false) final String email) {
    if (userRepository.findByEmail(email).isEmpty()) {
      return "User with email: " + email + " is not subscribed.";
    } else {
      userRepository.deleteByEmail(email);
      mailchimp.unsubscribe(email);
      return "Unsubscribed successfully";
    }
  }