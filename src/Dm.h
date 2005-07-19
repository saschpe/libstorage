#ifndef DM_H
#define DM_H

#include <map>

#include "y2storage/Volume.h"

class PeContainer;

class Dm : public Volume
    {
    public:
	Dm( const PeContainer& d, const string& tn );
	Dm( const PeContainer& d, const string& tn, unsigned mnum );
	Dm( const PeContainer& d, const Dm& d );
	Dm& operator=( const Dm& );

	virtual ~Dm();
	const string& getTableName() const { return( tname ); }
	const string& getTargetName() const { return( target ); }
	void setTableName( const string& name ) { tname=name; }
	unsigned long getLe() const { return num_le; }
	void setLe( unsigned long le );
	void calcSize();
	const std::map<string,unsigned long>& getPeMap() const { return( pe_map ); }
	void setPeMap( const std::map<string,unsigned long>& m ) { pe_map = m; }
	unsigned long usingPe( const string& dev ) const;
	void getTableInfo();
	virtual bool checkConsistency() const;
	unsigned stripes() const { return stripe; }
	unsigned long long stripeSize() const { return stripe_size; }
	void setStripeSize( unsigned long long val ) { stripe_size=val; }
	friend std::ostream& operator<< (std::ostream& s, const Dm &p );
	virtual void print( std::ostream& s ) const { s << *this; }
	virtual string removeText( bool doing ) const;
	virtual string formatText( bool doing ) const;
	void getInfo( storage::DmInfo& info ) const;

	static bool notDeleted( const Dm& l ) { return( !l.deleted() ); }

	static void activate( bool val=true );
	bool equalContent( const Dm& rhs ) const;
	void logDifference( const Dm& d ) const;
	string stringDifference( const Dm& d ) const;

    protected:
	void init();
	const PeContainer* const pec() const;
	virtual const string shortPrintedName() const { return( "Dm" ); }
	string getDevice( const string& majmin );
	static void getDmMajor();

	string tname;
	string target;
	unsigned long num_le;
	unsigned stripe;
	unsigned long long stripe_size;
	std::map<string,unsigned long> pe_map;
	static bool active;
	static unsigned dm_major;
	mutable storage::DmInfo info;
    };

#endif