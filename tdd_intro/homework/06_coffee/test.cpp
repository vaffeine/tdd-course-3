/*
We have to develop a coffee machine with TDD. The machine uses the automated source of ingredients, which implements the interface ISourceOfIngredients.

Our machine should be able to produce the coffee accordingly to the next receipts:
- americano: water & coffee 1:2 or 1:3. Water temp 60C
- cappuccino - milk & coffee & milk foam 1:3, 1:3, 1:3. Water temp 80C
- latte - milk & coffee & milk foam 1:4, 1:2, 1:4. Water temp 90C
- marochino - chocolate & coffee & milk foam, 1:4, 1:4, 1:4 and 1:4 is empty

We have 2 possible sizes of the cup:
- little 100 gram
- big 140 gram

Implement worked coffee machine using ISourceOfIngredients to controll the process of coffee production.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class ISourceOfIngredients
{
public:
    virtual ~ISourceOfIngredients() {}
    virtual void SetCupSize(int gram) = 0;
    virtual void AddWater(int gram, int temperature) = 0;
    virtual void AddSugar(int gram) = 0;
    virtual void AddCoffee(int gram) = 0;
    virtual void AddMilk(int gram) = 0;
    virtual void AddMilkFoam(int gram) = 0;
    virtual void AddChocolate(int gram) = 0;
    virtual void AddCream(int gram) = 0;
};


enum Cup
{
    Normal = 100,
    Big = 140,
};

enum Coffee
{
    Americano,
    Cappuccino,
};

class MockSourceOfIngredients : public ISourceOfIngredients
{
public:
    MOCK_METHOD1(SetCupSize, void(int));
    MOCK_METHOD2(AddWater, void(int, int));
    MOCK_METHOD1(AddSugar, void(int));
    MOCK_METHOD1(AddCoffee, void(int));
    MOCK_METHOD1(AddMilk, void(int));
    MOCK_METHOD1(AddMilkFoam, void(int));
    MOCK_METHOD1(AddChocolate, void(int));
    MOCK_METHOD1(AddCream, void(int));
};

class CoffeeMachine
{
public:
    CoffeeMachine(ISourceOfIngredients& source) : m_source(source)
    {

    }
    void CreateCoffee(const Cup cup, const Coffee coffee)
    {
        m_source.SetCupSize(cup);

        switch (cup) {
            case Cup::Normal:
                CreateNormalCoffee(coffee);
                break;
            case Cup::Big:
                CreateBigCoffee(coffee);
                break;
        }
    }

private:
    void CreateNormalCoffee(const Coffee coffee)
    {
        switch (coffee) {
            case Coffee::Americano:
                m_source.AddCoffee(75);
                m_source.AddWater(25, 60);
                break;
            case Coffee::Cappuccino:
                m_source.AddCoffee(33);
                m_source.AddMilk(33);
                m_source.AddMilkFoam(33);
                break;
        }
    }

    void CreateBigCoffee(const Coffee coffee)
    {
        switch (coffee) {
            case Coffee::Americano:
                m_source.AddCoffee(105);
                m_source.AddWater(35, 60);
                break;
        }
    }

private:
    ISourceOfIngredients& m_source;
};


// Architecture
// Class CoffeMachine
// Class-Mock SourceOfIngredients

// - americano: water & coffee 1:2 or 1:3. Water temp 60C

// Tests list:
// 1. americano + 100 gram = 1 coffe
// 2. americano + 140 gram = 1 large coffee
// 3. AddCoffee, SetCupSize and AddWater calls once
// 4. Check parameters
// 5. Same for each recipe

TEST(CoffeeMachine, CoffemachineIsHere)
{
    MockSourceOfIngredients si;
    CoffeeMachine cm(si);
}

TEST(CoffeeMachine, CallsImportantThings)
{
    MockSourceOfIngredients si;
    CoffeeMachine cm(si);

    EXPECT_CALL(si, AddCoffee(::testing::_)).Times(1);
    EXPECT_CALL(si, SetCupSize(::testing::_)).Times(1);
    EXPECT_CALL(si, AddWater(::testing::_, ::testing::_)).Times(1);

    cm.CreateCoffee(Cup::Normal, Coffee::Americano);
}

//- americano: water & coffee 1:3 Water temp 60C
TEST(CoffeeMachine, Americano)
{
    auto cup = Cup::Normal;
    MockSourceOfIngredients si;
    CoffeeMachine cm(si);

    EXPECT_CALL(si, AddCoffee(75)).Times(1);
    EXPECT_CALL(si, SetCupSize(cup)).Times(1);
    EXPECT_CALL(si, AddWater(25, 60)).Times(1);

    cm.CreateCoffee(cup, Coffee::Americano);
}

TEST(CoffeeMachine, AmericanoBig)
{
    auto cup = Cup::Big;
    MockSourceOfIngredients si;
    CoffeeMachine cm(si);

    EXPECT_CALL(si, AddCoffee(105)).Times(1);
    EXPECT_CALL(si, SetCupSize(cup)).Times(1);
    EXPECT_CALL(si, AddWater(35, 60)).Times(1);

    cm.CreateCoffee(cup, Coffee::Americano);
}

TEST(CoffeeMachine, Cappuccino)
{
    auto cup = Cup::Normal;
    MockSourceOfIngredients si;
    CoffeeMachine cm(si);

    EXPECT_CALL(si, SetCupSize(cup)).Times(1);
    EXPECT_CALL(si, AddCoffee(33)).Times(1);
    EXPECT_CALL(si, AddMilk(33)).Times(1);
    EXPECT_CALL(si, AddMilkFoam(33)).Times(1);

    cm.CreateCoffee(cup, Coffee::Cappuccino);
}

TEST(CoffeeMachine, CappuccinoBig)
{
    auto cup = Cup::Big;
    MockSourceOfIngredients si;
    CoffeeMachine cm(si);

    EXPECT_CALL(si, SetCupSize(cup)).Times(1);
    EXPECT_CALL(si, AddCoffee(46)).Times(1);
    EXPECT_CALL(si, AddMilk(46)).Times(1);
    EXPECT_CALL(si, AddMilkFoam(46)).Times(1);

    cm.CreateCoffee(cup, Coffee::Cappuccino);
}
