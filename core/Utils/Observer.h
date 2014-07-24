#ifndef OBSERVER_H
#define OBSERVER_H

#include <QtCore>

class Observer
{
public:
    virtual void Update() = 0;
};

class Observable
{
public:
    void Attach(Observer* observer)
    {
        m_observers.append(observer);
    }
    void Detach(Observer* observer)
    {
        m_observers.removeAll(observer);
    }

protected:
    void Notify()
    {
        QList<Observer*>::const_iterator i;
        for(i = m_observers.constBegin(); i != m_observers.constEnd(); ++i)
            (*i)->Update();
    }

    QList<Observer*> m_observers;
};

#endif // OBSERVER_H
