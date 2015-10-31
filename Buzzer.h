class Buzzer {
  public:
    static Buzzer &getInstance();

    static void tone(unsigned int frequency);
    static void tone(unsigned int frequency, unsigned long duration);
    static void stop();

  private:
    Buzzer() {};
    Buzzer(const Buzzer &other) {};
};
