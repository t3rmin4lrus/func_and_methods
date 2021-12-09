#include <iostream>
#include <string>
#include <vector>

// Задание 1:

template <class T>
class Pair1
{
private:
	T m_a;
	T m_b;

public:
	Pair1(const T& a, const T& b)
		: m_a(a), m_b(b)
	{
	}

	T& first() { return m_a; }
	const T& first() const { return m_a; }
	T& second() { return m_b; }
	const T& second() const { return m_b; }
};

// Задание 2:

template <class T, class S>
class Pair
{
private:
	T m_a;
	S m_b;

public:
	Pair(const T& a, const S& b)
		: m_a(a), m_b(b)
	{
	}

	T& first() { return m_a; }
	const T& first() const { return m_a; }
	S& second() { return m_b; }
	const S& second() const { return m_b; }
};

// Задание 3:

template <class ST, class XS>
class Pair2
{
private:
	ST m_a;
	XS m_b;

public:
	Pair2(const ST& a, const XS& b)
		: m_a(a), m_b(b)
	{
	}

	ST& first() { return m_a; }
	const ST& first() const { return m_a; }
	XS& second() { return m_b; }
	const XS& second() const { return m_b; }
};

template <class XS>
class StringValuePair : public Pair2<std::string, XS>
{
public:
	StringValuePair(const std::string& key, const XS& value)
		: Pair2<std::string, XS>(key, value)
	{
	}
};

// Задание 4:

class Card
{
public:
	enum rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
	enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };
	friend std::ostream& operator<<(std::ostream& os, const Card& aCard);

	Card(rank r = ACE, suit s = SPADES, bool ifu = true);

	int GetValue() const;

	void Flip();

private:
	rank m_Rank;
	suit m_Suit;
	bool m_IsFaceUp;
};

Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) {}

int Card::GetValue() const
{
	int value = 0;
	if (m_IsFaceUp)
	{
		value = m_Rank;
		if (value > 10)
		{
			value = 10;
		}
		return value;
	}
}

void Card::Flip()
{
	m_IsFaceUp = !(m_IsFaceUp);
}

class Hand
{
public:
	Hand();
	virtual ~Hand();
	void Add(Card* pCard);
	void Clear();
	int GetTotal() const;
protected:
	std::vector<Card*> m_Cards;
};

Hand::Hand()
{
	m_Cards.reserve(7);
}
Hand::~Hand()
{
	Clear();
}

void Hand::Add(Card* pCard)
{
	m_Cards.push_back(pCard);
}

void Hand::Clear()
{
	std::vector<Card*>::iterator iter = m_Cards.begin();
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
	{
		delete* iter;
		*iter = 0;
	}
	m_Cards.clear();
}

int Hand::GetTotal() const
{
	if (m_Cards.empty())
	{
		return 0;
	}
	if (m_Cards[0]->GetValue() == 0)
	{
		return 0;
	}
	int total = 0;
	std::vector<Card*>::const_iterator iter;
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
	{
		total += (*iter)->GetValue();
	}

	bool containsAce = false;
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
	{
		if ((*iter)->GetValue() == Card::ACE)
		{
			containsAce = true;
		}
	}

	if (containsAce && total <= 11)
	{
		total += 10;
	}
	return total;
}

class GenericPlayer : public Hand
{
	friend std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer);
    GenericPlayer(const std::string& name = " ");
    virtual ~GenericPlayer();
    virtual bool IsHitting() const = 0;
    bool IsBusted() const;
    void Bust() const;

protected:
    std::string m_Name;
};

GenericPlayer::GenericPlayer(const std::string& name) :
    m_Name(name)
{}
bool GenericPlayer::IsBusted() const
{
    return (GetTotal() > 21);
}

void GenericPlayer::Bust() const
{
    std::cout << m_Name << "Busts.\n";
}

int main()
{
  // Задание 1:

	Pair1<int> p1(6, 9);
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair1<double> p2(3.4, 7.8);
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    // Задание 2:

	Pair<int, double> p1(6, 7.8);
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair<double, int> p2(3.4, 5);
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    // Задание 3:
	StringValuePair<int> svp("Amazing", 7);
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

   return 0;
}