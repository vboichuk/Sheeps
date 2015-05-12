

#ifndef __Listener__
#define __Listener__

#include <iostream>
#include <list>

namespace Listener {
    
    template <class D>
	class IMethodDelegate {
	public:
		IMethodDelegate() { }
		virtual ~IMethodDelegate() { }
		virtual bool compare(IMethodDelegate<D>* delegate) const = 0;
		virtual bool compareObserver(void* observer) const = 0;
		virtual void invoke(void* sender, D data) const = 0;
	};

	template <class T, class D>
	class MethodDelegateData : public IMethodDelegate<D> {
	public:
		typedef void(T::*Method)(void*, D);
		bool compare(IMethodDelegate<D>* delegate) const {
			MethodDelegateData *pDel = dynamic_cast<MethodDelegateData*>(delegate);
			if ( !pDel || pDel->m_pObj != m_pObj || pDel->m_pMethod != m_pMethod)
				return false;
			return true;
		}
		virtual bool compareObserver(void* observer) const {
			return m_pObj == observer;
		}
		MethodDelegateData(T* obj, Method pMethod) {
			m_pObj = obj;
			m_pMethod = pMethod;
		}
		virtual void invoke(void *sender, D data) const {
			(m_pObj->*m_pMethod)(sender, data);
		}

	protected:
		T* m_pObj;
		Method m_pMethod;
	};

    //*************************************************************


    template <class D>
    class EventHandler {

       private:

           std::list<const IMethodDelegate<D>*> mDelegates;

           void add(const IMethodDelegate<D>* delegate) {
               mDelegates.push_back(delegate);
           }
           void remove(IMethodDelegate<D>* pdelegate) {
               for (typename std::list<const IMethodDelegate<D> * >::iterator it = mDelegates.begin(); it != mDelegates.end(); it++) {
                   if ((*it)->compare(pdelegate)) {
                       delete *it;
                       mDelegates.erase(it);
                       break;
                   }
               }
               delete pdelegate;
           }
           void removeAll() {
               for (typename std::list<const IMethodDelegate<D>*>::iterator it = mDelegates.begin(); it != mDelegates.end(); it++) {
                   delete *it;
               }
               mDelegates.clear();
           }

       public:

           virtual ~EventHandler() { removeAll(); }

           EventHandler& operator += (const IMethodDelegate<D>* delegate) {
               this->add(delegate);
               return *this;
           }

           EventHandler& operator -= (IMethodDelegate<D>* delegate) {
               remove(delegate);
               return *this;
           }

           EventHandler& removeObserver (void* observer) {
				for (typename std::list<const IMethodDelegate<D>*>::iterator it = mDelegates.begin(); it != mDelegates.end(); it++) {
					if ((*it)->compareObserver(observer)) {
						delete *it;
						mDelegates.erase(it);
					}
					else
						it++;
				}
                return *this;
           }

           virtual void invoke(void *sender, D data) {
			  for (typename std::list<const IMethodDelegate<D>*>::iterator it = mDelegates.begin(); it != mDelegates.end(); it++) {
				  (*it)->invoke(sender, data);
			  }
		  }
       };
}
#endif /* defined(__Listener__) */
