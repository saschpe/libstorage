#ifndef LOOP_CO_H
#define LOOP_CO_H

#include "y2storage/Container.h"
#include "y2storage/Loop.h"

class LoopCo : public Container
    {
    friend class Storage;

    public:
	LoopCo( Storage * const s, bool detect );
	LoopCo( const LoopCo& rhs );

	virtual ~LoopCo();
	static storage::CType const staticType() { return storage::LOOP; }
	friend std::ostream& operator<< (std::ostream&, const LoopCo& );

	int createLoop( const string& file, bool reuseExisting, 
	                unsigned long long sizeK, string& device );
	int removeLoop( const string& file, bool removeFile = false );

	int removeVolume( Volume* v );
	bool equalContent( const LoopCo& rhs ) const;
	void logDifference( const LoopCo& d ) const;
	
    protected:
	// iterators over LOOP volumes
	// protected typedefs for iterators over LOOP volumes
	typedef CastIterator<VIter, Loop *> LoopInter;
	typedef CastIterator<CVIter, const Loop *> LoopCInter;
	template< class Pred >
	    struct LoopPI { typedef ContainerIter<Pred, LoopInter> type; };
	template< class Pred >
	    struct LoopCPI { typedef ContainerIter<Pred, LoopCInter> type; };
	typedef CheckFnc<const Loop> CheckFncLoop;
	typedef CheckerIterator< CheckFncLoop, LoopPI<CheckFncLoop>::type,
				 LoopInter, Loop > LoopPIterator;
	typedef CheckerIterator< CheckFncLoop, LoopCPI<CheckFncLoop>::type,
				 LoopCInter, const Loop > LoopCPIterator;
	typedef DerefIterator<LoopPIterator,Loop> LoopIter;
	typedef DerefIterator<LoopCPIterator,const Loop> ConstLoopIter;
	typedef IterPair<LoopIter> LoopPair;
	typedef IterPair<ConstLoopIter> ConstLoopPair;

	LoopPair loopPair( bool (* Check)( const Loop& )=NULL)
	    {
	    return( LoopPair( loopBegin( Check ), loopEnd( Check ) ));
	    }
	LoopIter loopBegin( bool (* Check)( const Loop& )=NULL)
	    {
	    IterPair<LoopInter> p( (LoopInter(begin())), (LoopInter(end())) );
	    return( LoopIter( LoopPIterator( p, Check )) );
	    }
	LoopIter loopEnd( bool (* Check)( const Loop& )=NULL)
	    {
	    IterPair<LoopInter> p( (LoopInter(begin())), (LoopInter(end())) );
	    return( LoopIter( LoopPIterator( p, Check, true )) );
	    }

	ConstLoopPair loopPair( bool (* Check)( const Loop& )=NULL) const
	    {
	    return( ConstLoopPair( loopBegin( Check ), loopEnd( Check ) ));
	    }
	ConstLoopIter loopBegin( bool (* Check)( const Loop& )=NULL) const
	    {
	    IterPair<LoopCInter> p( (LoopCInter(begin())), (LoopCInter(end())) );
	    return( ConstLoopIter( LoopCPIterator( p, Check )) );
	    }
	ConstLoopIter loopEnd( bool (* Check)( const Loop& )=NULL) const
	    {
	    IterPair<LoopCInter> p( (LoopCInter(begin())), (LoopCInter(end())) );
	    return( ConstLoopIter( LoopCPIterator( p, Check, true )) );
	    }

	LoopCo( Storage * const s, const string& File );

	void getLoopData();
	bool findLoop( unsigned num, LoopIter& i );
	bool findLoop( unsigned num ); 
	bool findLoop( const string& dev, LoopIter& i );
	bool findLoop( const string& dev ); 
	void addLoop( Loop* m );
	void checkLoop( Loop* m );
	void updateEntry( const Loop* m );
	static int getFreeLoop( string& dev );

	void init();

	virtual void print( std::ostream& s ) const { s << *this; }
	virtual Container* getCopy() const { return( new LoopCo( *this ) ); }

	int doCreate( Volume* v );
	int doRemove( Volume* v );

	void logData( const string& Dir );
    };

#endif