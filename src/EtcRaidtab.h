#ifndef ETC_RAIDTAB_H
#define ETC_RAIDTAB_H

#include <string>
#include <map>

class AsciiFile;

class EtcRaidtab
    {
    public:
	EtcRaidtab( const string& prefix="" );
	~EtcRaidtab();
	void updateEntry( unsigned num, const std::list<string>& entries,
	                  const string&, const std::list<string>& devs );
	void removeEntry( unsigned num );
    protected:
	struct entry
	    {
	    entry() { first=last=0; }
	    entry( unsigned f, unsigned l ) { first=f; last=l; }
	    unsigned first;
	    unsigned last;
	    friend std::ostream& operator<< (std::ostream& s, const entry &v );
	    };
	friend std::ostream& operator<< (std::ostream& s, const entry &v );

	void updateMdadmFile();
	void updateRaidtabFile();
	void buildRaidtabMap();
	void buildMdadmMap();

	Regex *whitespace;
	Regex *comment;
	string rtabname;
	string mdadmname;
	int mdadm_dev_line;
	std::map<unsigned,entry> mtab;
	std::map<unsigned,entry> rtab;
	AsciiFile* raidtab;
	AsciiFile* mdadm;
    };
///////////////////////////////////////////////////////////////////

inline std::ostream& operator<< (std::ostream& s, const EtcRaidtab::entry& v )
    {
    s << "first=" << v.first << " last=" << v.last;
    return( s );
    }

#endif