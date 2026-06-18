
class EasyBot;
class HardBot;

class Bot {
public:
   virtual ~Bot() = default;

   virtual int move() const = 0;
};

class EasyBot : public Bot {
public:
   int move() const override;
};

class HardBot : public Bot {
public:
   int move() const override;

};