#ifndef MIDI_JOURNAL_H
#define MIDI_JOURNAL_H

typedef struct journal_header_t {
	unsigned char	totchan:4;
	unsigned char	bitfield:4; // SYAH
	uint16_t	seq;
} journal_header_t;

typedef struct channel_header_t {
	unsigned int	len:10;
	unsigned char	H:1;
	unsigned char	chan:4;
	unsigned char	S:1;
	uint8_t		bitfield; // PCMWNETA
} channel_header_t;

#define CHAPTER_P	0x80
#define CHAPTER_C	0x40
#define CHAPTER_M	0x20
#define CHAPTER_W	0x10
#define CHAPTER_N	0x08
#define CHAPTER_E	0x04
#define CHAPTER_T	0x02
#define CHAPTER_A	0x01

#define MAX_CHAPTERN_NOTES	127
#define MAX_OFFBITS		16

typedef struct chaptern_header_t {
	unsigned char	high:4;
	unsigned char	low:4;
	unsigned char	len:7;
	unsigned char	B:1;
} chaptern_header_t;

typedef struct midi_note_t {
	unsigned char	velocity:7;
	unsigned char	Y:1;
	unsigned char	num:7;
	unsigned char	S:1;
} midi_note_t;

typedef struct chaptern_t {
	chaptern_header_t	*header;
	uint16_t		num_notes;
	midi_note_t 		*notes[MAX_CHAPTERN_NOTES];
	char			*offbits;
} chaptern_t;

typedef struct channel_t {
	channel_header_t *header;
	chaptern_t *chaptern;
} channel_t;

#define MAX_MIDI_CHANNELS	16

typedef struct journal_t {
	journal_header_t *header;
	channel_t *channels[MAX_MIDI_CHANNELS];
} journal_t;


journal_header_t * journal_header_create( void );
void journal_header_destroy( journal_header_t **header);

channel_header_t * channel_header_create( void );
void channel_header_destroy( channel_header_t **header );

chaptern_header_t * chaptern_header_create( void );
void chaptern_header_destroy( chaptern_header_t **header );

midi_note_t * midi_note_create( void );
void midi_note_destroy( midi_note_t **note );

chaptern_t * chaptern_create( void );
void chaptern_destroy( chaptern_t **chaptern );

channel_t * channel_create( void );
void channel_destroy( channel_t **channel );

int journal_init( journal_t **journal );
void journal_destroy( journal_t **journal );

void midi_journal_add_note( journal_t *journal, uint32_t seq, char channel, char note, char velocity );

void channel_header_dump( channel_header_t *header );
void channel_journal_dump( channel_t *channel );
void journal_header_dump( journal_header_t *header );
void journal_dump( journal_t *journal );

#endif
