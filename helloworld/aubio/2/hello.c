#include <stdio.h>
#include "aubio/aubio.h"

FILE *out;
const char_t *hdr = "";
void logging(int level, const char_t *message, void *data)
{
  if ((level >= 0) && (data != NULL))
  {
    fprintf(out, "%s", (const char_t *)data);
  }
  fprintf(out, "%s", message);
}

int main (void)
{
  uint_t samplerate = 0;
  uint_t hop_size = 160;
  uint_t n_frames = 0, read = 0;

  aubio_source_t* s = new_aubio_source("../1188-133604-0025.flac.wav",
    samplerate, hop_size);
  fvec_t * vec = new_fvec(hop_size);

  out = fopen("log_x.txt","w");
  aubio_log_set_function(logging, (void *)hdr);

  if (samplerate == 0)
  {
    samplerate = aubio_source_get_samplerate(s);
    printf("samplerate:%d\n", samplerate);
  }

  do
  {
    aubio_source_do(s, vec, &read);
    fvec_print (vec);
    n_frames += read;
  } while ( read == hop_size );

  del_fvec (vec);
  del_aubio_source (s);
  fclose(out);

  return 0;
}
